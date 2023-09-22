#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "/home/daniel/Pulled/raygui/src/raygui.c"

int open_window(struct PtpRuntime *r) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(720 + 100, 480 + 100, "cam");

	//SetConfigFlags(FLAG_VSYNC_HINT);

	SetTargetFPS(30);

	Image lv;
	lv.data = malloc(SCREEN_WIDTH * SCREEN_WIDTH * sizeof(Color));
	lv.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
	lv.width = SCREEN_WIDTH;
	lv.height = SCREEN_HEIGHT;
	lv.mipmaps = 1;

	Color *pixels = (Color *)lv.data;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		pixels[i] = ORANGE;
	}

	Texture2D tex = LoadTextureFromImage(lv);

	int rc = init_ptp(r);

	while (!WindowShouldClose())	// Detect window close button or ESC key
	{
		BeginDrawing();
			ClearBackground(BLACK);

			if (rc == 0) {
				rc = render_lv(r, pixels);
				printf("Error: %d\n", rc);
				if (rc) {
					return -1;
				}
			}

			UpdateTexture(tex, pixels);

			DrawTexture(tex, (GetScreenWidth() - SCREEN_WIDTH) / 2, (GetScreenHeight() - SCREEN_HEIGHT) / 2, WHITE);

			if (rc) {
				DrawText("Error connecting to camera", 4, 4, 20, RED);
			}

			 GuiLabel((Rectangle){ 555, 195, 110, 10 }, "BORDER_WIDTH");
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
