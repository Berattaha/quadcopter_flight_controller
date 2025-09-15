#include <TaskManagerIO.h>

void initializeOutputSignals() {
  pinMode(LED_YESIL_PIN, OUTPUT);
  pinMode(LED_KIRMIZI_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_YESIL_PIN, LOW);
  digitalWrite(LED_KIRMIZI_PIN, HIGH);
  noTone(BUZZER_PIN);
}

void syncOutputSignals() {
  taskManager.runLoop();
}

void quadcopter_initialization_completed() {
//  blink_led();
  taskManager.execute([] {
    tone(BUZZER_PIN, 2000);
    taskManager.scheduleOnce(1000, [] {
      noTone(BUZZER_PIN);
    });
  });
}

bool ledIsOn = false;
int ledBlinkTaskId;

/*void blink_led() {
  ledBlinkTaskId = taskManager.scheduleFixedRate(500, [] {
    if (ledIsOn) {
      digitalWrite(LED_PIN, LOW);
    } else{
      digitalWrite(LED_PIN, HIGH);
    }
    ledIsOn = !ledIsOn;
  });
}*/

void quadcopter_armed() {
  taskManager.cancelTask(ledBlinkTaskId);
  taskManager.execute([] {
    digitalWrite(LED_YESIL_PIN, HIGH);
    digitalWrite(LED_KIRMIZI_PIN, LOW);
    tone(BUZZER_PIN, 500);
    taskManager.scheduleOnce(500, [] {
      tone(BUZZER_PIN, 1000);
      taskManager.scheduleOnce(500, [] {
        tone(BUZZER_PIN, 1500);
        taskManager.scheduleOnce(500, [] {
          noTone(BUZZER_PIN);
        });
      });
    });
  });
}

void quadcopter_disarmed() {
  //blink_led();
  taskManager.execute([] {
    digitalWrite(LED_YESIL_PIN, LOW);
    digitalWrite(LED_KIRMIZI_PIN, HIGH);
    tone(BUZZER_PIN, 1500);
    taskManager.scheduleOnce(500, [] {
      tone(BUZZER_PIN, 1000);
      taskManager.scheduleOnce(500, [] {
        tone(BUZZER_PIN, 500);
        taskManager.scheduleOnce(500, [] {
          noTone(BUZZER_PIN);
        });
      });
    });
  });
}
