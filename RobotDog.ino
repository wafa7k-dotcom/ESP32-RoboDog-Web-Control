
#include <WiFi.h>
#include <WebServer.h>

// =====================================
// شبكة التحكم
// =====================================
const char* AP_NAME = "RoboDog-Control";
const char* AP_PASSWORD = "12345678";

WebServer server(80);

// =====================================
// الأرجل
// =====================================
const int FL_PIN = 4;   // الأمامية اليسار
const int FR_PIN = 16;  // الأمامية اليمين — معكوسة
const int RL_PIN = 22;  // الخلفية اليسار
const int RR_PIN = 25;  // الخلفية اليمين — معكوسة

// وضع الوقوف للجميع
const int STAND_ANGLE = 90;

// القيم الحالية
int flAngle = 90;
int frAngle = 90;
int rlAngle = 90;
int rrAngle = 90;

// =====================================
// إرسال الزاوية للسيرفو
// =====================================
void writeServo(int pin, int logicalAngle) {
  logicalAngle = constrain(logicalAngle, 40, 140);

  int physicalAngle = logicalAngle;

  // عكس سيرفوات جهة اليمين
  if (pin == FR_PIN || pin == RR_PIN) {
    physicalAngle = 180 - logicalAngle;
  }

  physicalAngle = constrain(physicalAngle, 40, 140);

  int pulseUs = map(
    physicalAngle,
    0,
    180,
    500,
    2500
  );

  uint32_t duty =
    ((uint32_t)pulseUs * 65535UL) / 20000UL;

  ledcWrite(pin, duty);
}

// =====================================
// تحريك الأربع أرجل معًا بالتدريج
// =====================================
void moveAllSmooth(
  int targetFL,
  int targetFR,
  int targetRL,
  int targetRR,
  int stepDelay = 15
) {
  targetFL = constrain(targetFL, 40, 140);
  targetFR = constrain(targetFR, 40, 140);
  targetRL = constrain(targetRL, 40, 140);
  targetRR = constrain(targetRR, 40, 140);

  int startFL = flAngle;
  int startFR = frAngle;
  int startRL = rlAngle;
  int startRR = rrAngle;

  int steps = max(
    max(
      abs(targetFL - startFL),
      abs(targetFR - startFR)
    ),
    max(
      abs(targetRL - startRL),
      abs(targetRR - startRR)
    )
  );

  if (steps == 0) {
    writeServo(FL_PIN, targetFL);
    writeServo(FR_PIN, targetFR);
    writeServo(RL_PIN, targetRL);
    writeServo(RR_PIN, targetRR);
    return;
  }

  for (int step = 1; step <= steps; step++) {
    int newFL =
      startFL + ((targetFL - startFL) * step) / steps;

    int newFR =
      startFR + ((targetFR - startFR) * step) / steps;

    int newRL =
      startRL + ((targetRL - startRL) * step) / steps;

    int newRR =
      startRR + ((targetRR - startRR) * step) / steps;

    writeServo(FL_PIN, newFL);
    writeServo(FR_PIN, newFR);
    writeServo(RL_PIN, newRL);
    writeServo(RR_PIN, newRR);

    delay(stepDelay);
  }

  flAngle = targetFL;
  frAngle = targetFR;
  rlAngle = targetRL;
  rrAngle = targetRR;
}

// =====================================
// وضع الوقوف — كلها 90
// =====================================
void standPosition() {
  moveAllSmooth(90, 90, 90, 90, 18);
  delay(300);
}

// =====================================
// المشي للأمام
// =====================================
void walkForward() {
  standPosition();

  for (int i = 0; i < 3; i++) {
    // الأمامية اليسار + الخلفية اليمين
    moveAllSmooth(78, 90, 90, 78, 18);
    delay(300);

    moveAllSmooth(90, 90, 90, 90, 18);
    delay(150);

    // الأمامية اليمين + الخلفية اليسار
    moveAllSmooth(90, 102, 102, 90, 18);
    delay(300);

    moveAllSmooth(90, 90, 90, 90, 18);
    delay(150);
  }

  standPosition();
}

// =====================================
// المشي للخلف
// =====================================
void walkBackward() {
  standPosition();

  for (int i = 0; i < 3; i++) {
    moveAllSmooth(102, 90, 90, 102, 18);
    delay(300);

    moveAllSmooth(90, 90, 90, 90, 18);
    delay(150);

    moveAllSmooth(90, 78, 78, 90, 18);
    delay(300);

    moveAllSmooth(90, 90, 90, 90, 18);
    delay(150);
  }

  standPosition();
}

// =====================================
// المصافحة بالأمامية اليمنى
// =====================================
void shakeHand() {
  standPosition();

  // ميل خفيف لتثبيت الجسم
  moveAllSmooth(84, 90, 96, 90, 18);
  delay(350);

  for (int i = 0; i < 4; i++) {
    moveAllSmooth(84, 105, 96, 90, 18);
    delay(220);

    moveAllSmooth(84, 78, 96, 90, 18);
    delay(220);
  }

  standPosition();
}

// =====================================
// الرقص
// =====================================
void danceRobot() {
  standPosition();

  for (int i = 0; i < 4; i++) {
    moveAllSmooth(78, 78, 78, 78, 18);
    delay(350);

    moveAllSmooth(90, 90, 90, 90, 18);
    delay(150);

    moveAllSmooth(102, 102, 102, 102, 18);
    delay(350);

    moveAllSmooth(90, 90, 90, 90, 18);
    delay(150);
  }

  standPosition();
}

// =====================================
// الجلوس
// =====================================
void sitRobot() {
  standPosition();

  moveAllSmooth(100, 80, 78, 102, 22);
  delay(1200);

  standPosition();
}

// =====================================
// الانحناء
// =====================================
void bowRobot() {
  standPosition();

  moveAllSmooth(78, 102, 102, 78, 22);
  delay(1000);

  standPosition();
}

// =====================================
// واجهة التحكم
// =====================================
const char MAIN_PAGE[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="ar" dir="rtl">

<head>
  <meta charset="UTF-8">

  <meta name="viewport"
        content="width=device-width,initial-scale=1">

  <title>RoboDog Control</title>

  <style>
    * {
      box-sizing: border-box;
    }

    body {
      margin: 0;
      padding: 18px;
      min-height: 100vh;
      color: white;
      text-align: center;
      font-family: Arial, sans-serif;
      background: linear-gradient(135deg,#0f172a,#1e293b);
    }

    .container {
      width: 100%;
      max-width: 700px;
      margin: auto;
    }

    h1 {
      color: #38bdf8;
    }

    #status {
      min-height: 28px;
      margin: 12px;
      color: #facc15;
      font-weight: bold;
    }

    .connected {
      color: #86efac;
    }

    .card {
      margin: 14px 0;
      padding: 17px;
      border-radius: 18px;
      background: rgba(255,255,255,0.08);
    }

    .buttons {
      display: grid;
      grid-template-columns: 1fr 1fr;
      gap: 9px;
    }

    button {
      padding: 16px 8px;
      border: none;
      border-radius: 13px;
      color: white;
      font-size: 17px;
      font-weight: bold;
    }

    button:active {
      transform: scale(0.97);
    }

    .forward { background:#22c55e; }
    .backward { background:#f97316; }
    .shake { background:#8b5cf6; }
    .dance { background:#ec4899; }
    .sit { background:#6366f1; }
    .bow { background:#14b8a6; }
    .stand { background:#0ea5e9; }
    .stop { background:#ef4444; }

    .servo-name {
      font-size: 17px;
      font-weight: bold;
    }

    .angle {
      margin: 8px;
      color: #38bdf8;
      font-size: 26px;
      font-weight: bold;
    }

    input[type=range] {
      width: 100%;
      accent-color: #38bdf8;
    }

    @media(max-width:450px) {
      .buttons {
        grid-template-columns: 1fr;
      }
    }
  </style>
</head>

<body>

<div class="container">

  <h1>🐕 RoboDog Control</h1>

  <div class="connected">
    متصل — 192.168.4.1
  </div>

  <div id="status">الروبوت جاهز</div>

  <div class="card">
    <div class="buttons">

      <button class="forward"
              onclick="runMovement('/forward','المشي للأمام')">
        ⬆️ أمام
      </button>

      <button class="backward"
              onclick="runMovement('/backward','المشي للخلف')">
        ⬇️ خلف
      </button>

      <button class="shake"
              onclick="runMovement('/shake','المصافحة')">
        👋 مصافحة
      </button>

      <button class="dance"
              onclick="runMovement('/dance','الرقص')">
        💃 رقص
      </button>

      <button class="sit"
              onclick="runMovement('/sit','الجلوس')">
        🐕 جلوس
      </button>

      <button class="bow"
              onclick="runMovement('/bow','الانحناء')">
        🙇 انحناء
      </button>

      <button class="stand"
              onclick="standRobot()">
        ✅ وقوف 90°
      </button>

      <button class="stop"
              onclick="standRobot()">
        🛑 إيقاف
      </button>

    </div>
  </div>

  <div class="card">
    <div class="servo-name">
      الأمامية اليسار — GPIO4
    </div>

    <div id="FLvalue" class="angle">90°</div>

    <input id="FL"
           type="range"
           min="60"
           max="120"
           value="90"
           oninput="setServo('FL',this.value)">
  </div>

  <div class="card">
    <div class="servo-name">
      الأمامية اليمين — GPIO16
    </div>

    <div id="FRvalue" class="angle">90°</div>

    <input id="FR"
           type="range"
           min="60"
           max="120"
           value="90"
           oninput="setServo('FR',this.value)">
  </div>

  <div class="card">
    <div class="servo-name">
      الخلفية اليسار — GPIO22
    </div>

    <div id="RLvalue" class="angle">90°</div>

    <input id="RL"
           type="range"
           min="60"
           max="120"
           value="90"
           oninput="setServo('RL',this.value)">
  </div>

  <div class="card">
    <div class="servo-name">
      الخلفية اليمين — GPIO25
    </div>

    <div id="RRvalue" class="angle">90°</div>

    <input id="RR"
           type="range"
           min="60"
           max="120"
           value="90"
           oninput="setServo('RR',this.value)">
  </div>

</div>

<script>
  let running = false;

  function showStatus(text) {
    document.getElementById("status").innerText = text;
  }

  async function runMovement(path, name) {
    if (running) {
      showStatus("انتظري حتى تنتهي الحركة");
      return;
    }

    running = true;
    showStatus("جاري تنفيذ: " + name);

    try {
      const response = await fetch(
        path + "?time=" + Date.now(),
        { cache: "no-store" }
      );

      if (!response.ok) {
        throw new Error("Movement failed");
      }

      showStatus("تم تنفيذ: " + name);
      resetSliders();
    }
    catch (error) {
      showStatus("تعذر تنفيذ الحركة");
    }

    running = false;
  }

  function setServo(leg, angle) {
    document.getElementById(
      leg + "value"
    ).innerText = angle + "°";

    fetch(
      "/set?leg=" + leg +
      "&angle=" + angle +
      "&time=" + Date.now(),
      { cache: "no-store" }
    ).catch(function() {
      showStatus("تعذر تحريك السيرفو");
    });
  }

  function resetSliders() {
    const values = {
      FL: 90,
      FR: 90,
      RL: 90,
      RR: 90
    };

    Object.keys(values).forEach(function(leg) {
      document.getElementById(leg).value = 90;
      document.getElementById(leg + "value").innerText = "90°";
    });
  }

  function standRobot() {
    resetSliders();
    runMovement("/stand", "وضع الوقوف");
  }
</script>

</body>
</html>
)HTML";

// =====================================
// السلايدرات اليدوية
// =====================================
void handleSetServo() {
  if (!server.hasArg("leg") ||
      !server.hasArg("angle")) {
    server.send(400, "text/plain", "Missing arguments");
    return;
  }

  String leg = server.arg("leg");

  int angle = constrain(
    server.arg("angle").toInt(),
    60,
    120
  );

  if (leg == "FL") {
    flAngle = angle;
    writeServo(FL_PIN, angle);
  }
  else if (leg == "FR") {
    frAngle = angle;
    writeServo(FR_PIN, angle);
  }
  else if (leg == "RL") {
    rlAngle = angle;
    writeServo(RL_PIN, angle);
  }
  else if (leg == "RR") {
    rrAngle = angle;
    writeServo(RR_PIN, angle);
  }
  else {
    server.send(400, "text/plain", "Invalid leg");
    return;
  }

  server.send(200, "text/plain", "OK");
}

// =====================================
// Setup
// =====================================
void setup() {
  Serial.begin(115200);

  ledcAttach(FL_PIN, 50, 16);
  ledcAttach(FR_PIN, 50, 16);
  ledcAttach(RL_PIN, 50, 16);
  ledcAttach(RR_PIN, 50, 16);

  delay(300);

  // كلها تبدأ على 90
  standPosition();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME, AP_PASSWORD);

  Serial.println();
  Serial.println("RoboDog ready");
  Serial.print("Network: ");
  Serial.println(AP_NAME);
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", []() {
    server.sendHeader(
      "Cache-Control",
      "no-store, no-cache, must-revalidate"
    );

    server.send_P(
      200,
      "text/html; charset=utf-8",
      MAIN_PAGE
    );
  });

  server.on("/set", handleSetServo);

  // الحركة تنفذ أولًا ثم يرسل الرد
  server.on("/forward", []() {
    walkForward();
    server.send(200, "text/plain", "Forward done");
  });

  server.on("/backward", []() {
    walkBackward();
    server.send(200, "text/plain", "Backward done");
  });

  server.on("/shake", []() {
    shakeHand();
    server.send(200, "text/plain", "Shake done");
  });

  server.on("/dance", []() {
    danceRobot();
    server.send(200, "text/plain", "Dance done");
  });

  server.on("/sit", []() {
    sitRobot();
    server.send(200, "text/plain", "Sit done");
  });

  server.on("/bow", []() {
    bowRobot();
    server.send(200, "text/plain", "Bow done");
  });

  server.on("/stand", []() {
    standPosition();
    server.send(200, "text/plain", "Stand done");
  });

  server.begin();

  Serial.println("Open:");
  Serial.println("http://192.168.4.1");
}

// =====================================
// Loop
// =====================================
void loop() {
  server.handleClient();
}