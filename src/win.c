#include <camlib.h>

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "/home/daniel/Pulled/raygui/src/raygui.c"

int camit_open_window(struct PtpRuntime *r) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(720 + 100, 480 + 100, "cam");

	//SetConfigFlags(FLAG_VSYNC_HINT);

	int lv_width = 720;
	int lv_height = 480;

	SetTargetFPS(30);

	Image lv;
	lv.data = malloc(lv_width * lv_width * sizeof(Color));
	lv.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
	lv.width = lv_width;
	lv.height = lv_height;
	lv.mipmaps = 1;

	Color *pixels = (Color *)lv.data;
	for (int i = 0; i < lv_width * lv_height; i++) {
		pixels[i] = ORANGE;
	}

	Texture2D tex = LoadTextureFromImage(lv);

	while (!WindowShouldClose())	// Detect window close button or ESC key
	{
		BeginDrawing();
			ClearBackground(BLACK);

			// if (rc == 0) {
				// rc = render_lv(r, pixels);
				// printf("Error: %d\n", rc);
				// if (rc) {
					// return -1;
				// }
			// }

			UpdateTexture(tex, pixels);

			DrawTexture(tex, (GetScreenWidth() - lv_width) / 2, (GetScreenHeight() - lv_height) / 2, WHITE);

//			if (rc) {
				DrawText("Error connecting to camera", 4, 4, 20, RED);
//			}

			if (GuiButton((Rectangle){100, 10, 150, 30 }, "Disconnect")) {
				printf("Hello, World\n");
			}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
