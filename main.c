#include <raylib.h>
#include <stdint.h>
#include <stdio.h>

#define WINDOW_TITLE "raptors-and-prey"
#define SCR_W 1280
#define SCR_H 720
#define FPS 60
#define RESET_STR "Reset"
#define STEP_STR "Step"

#define MAIN_FONT_SIZE 32
#define GAP 12
#define STR_SIZE 128

#define FEMALE_WOLF 0
#define MALE_WOLF 1
#define RABBIT 2

static uint16_t amount[3] = {
    10,	// FEMALE_WOLF
    10,	// MALE_WOLF
    20,	// RABBIT
};
static char amount_str[3][STR_SIZE];

static uint64_t day = 1;
static char day_str[STR_SIZE];

static Rectangle amount_btn_rects[3][2];
static Rectangle reset_rec;
static Rectangle step_rec;

int main(void) {
  InitWindow(SCR_W, SCR_H, WINDOW_TITLE);
  SetTargetFPS(FPS);

  // INIT BEGIN
  for (int i = 0; i < 3; i++) {
    amount_btn_rects[i][0] =
        (Rectangle){.x = GAP,
                    .y = MAIN_FONT_SIZE * i + GAP * (i + 1),
                    .width = MAIN_FONT_SIZE,
                    .height = MAIN_FONT_SIZE};
    amount_btn_rects[i][1] =
        (Rectangle){.x = GAP * 2 + MAIN_FONT_SIZE,
                    .y = MAIN_FONT_SIZE * i + GAP * (i + 1),
                    .width = MAIN_FONT_SIZE,
                    .height = MAIN_FONT_SIZE};
  }
  int far_x = SCR_W - MAIN_FONT_SIZE * 12;
  reset_rec = (Rectangle){.x = far_x,
                          .y = GAP,
                          .width = MeasureText(RESET_STR, MAIN_FONT_SIZE),
                          .height = MAIN_FONT_SIZE};
  step_rec = (Rectangle){.x = far_x,
                         .y = MAIN_FONT_SIZE + GAP * 2,
                         .width = MeasureText(STEP_STR, MAIN_FONT_SIZE),
                         .height = MAIN_FONT_SIZE};
  // INIT END

  while (!WindowShouldClose()) {
    snprintf(amount_str[FEMALE_WOLF], STR_SIZE, "Female wolfs: %d",
             amount[FEMALE_WOLF]);
    snprintf(amount_str[MALE_WOLF], STR_SIZE, "Male wolfs: %d",
             amount[MALE_WOLF]);
    snprintf(amount_str[RABBIT], STR_SIZE, "Rabbits: %d", amount[RABBIT]);
    snprintf(day_str, STR_SIZE, "Day: %d", day);

    // INPUT BEGIN
    if (IsMouseButtonPressed(0)) {
      Vector2 mouse = GetMousePosition();
      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
          if (CheckCollisionPointRec(mouse, amount_btn_rects[i][j])) {
            if (j == 0)
              amount[i] += 1;
            else
              amount[i] -= 1;
            goto inputEnd;
          }
      if (CheckCollisionPointRec(mouse, reset_rec))
        printf("Reset...\n");
      else if (CheckCollisionPointRec(mouse, step_rec))
        printf("Step...\n");
    }
  inputEnd:
    // INPUT END

    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++) {
          DrawRectangleRec(amount_btn_rects[i][j], LIGHTGRAY);
          DrawText(j == 0 ? "+" : "-", amount_btn_rects[i][j].x + GAP / 2,
                   amount_btn_rects[i][j].y, MAIN_FONT_SIZE, BLACK);
        }

      int x = GAP * 3 + MAIN_FONT_SIZE * 2;
      DrawText(amount_str[FEMALE_WOLF], x, GAP, MAIN_FONT_SIZE, BLACK);
      DrawText(amount_str[MALE_WOLF], x, MAIN_FONT_SIZE + GAP * 2,
               MAIN_FONT_SIZE, BLACK);
      DrawText(amount_str[RABBIT], x, MAIN_FONT_SIZE * 2 + GAP * 3,
               MAIN_FONT_SIZE, BLACK);

      int far_x = SCR_W - MAIN_FONT_SIZE * 12;
      DrawRectangleRec(reset_rec, LIGHTGRAY);
      DrawText(RESET_STR, far_x, GAP, MAIN_FONT_SIZE, BLACK);

      DrawRectangleRec(step_rec, LIGHTGRAY);
      DrawText(STEP_STR, far_x, MAIN_FONT_SIZE + GAP * 2, MAIN_FONT_SIZE,
               BLACK);

      DrawText(day_str, far_x, MAIN_FONT_SIZE * 2 + GAP * 3, MAIN_FONT_SIZE,
               BLACK);
    }
    EndDrawing();
  }
}
