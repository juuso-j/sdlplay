#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
typedef struct {
	int x;
	int y;
	int type;
} kernel;
const int width = 400;
const int height = 400;
int main(int argc, char** argv)
{
	bool leftMouseButtonDown = false;
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("SDL2 Pixel Drawing",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
	Uint32* pixels = new Uint32[640 * 480];

	memset(pixels, 0, width * height * sizeof(Uint32));
	int num_kernels = 10000;
	//kernel kernels[num_kernels];
	kernel* kernels = (kernel*) malloc(num_kernels * sizeof(kernel));
	for (int i = 0; i < num_kernels; i++) {
		kernels[i].x =150+ (rand() % (width-300));
		kernels[i].y =1+ (rand() % (height-122));
		kernels[i].type = 1;
		//printf("|| x: %i y: %i", kernels[i].x, kernels[i].y);
	}


	SDL_Event e;
	unsigned int frames = 0;
	Uint64 start = SDL_GetPerformanceCounter();

	while (!quit)
	{
		SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));
		//memset(pixels, 0, width * height * sizeof(Uint32));
		//SDL_WaitEvent(&event);
		SDL_PollEvent(&e);
		
		num_kernels++;
		kernels = (kernel*)realloc(kernels, num_kernels * sizeof(kernel));
		kernels[num_kernels - 1].x = width/2;
		kernels[num_kernels - 1].y = 1;
		kernels[num_kernels - 1].type = 1;

		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			int mouseX = e.motion.x;
			int mouseY = e.motion.y;
			num_kernels++;
			kernels = (kernel*)realloc(kernels,num_kernels * sizeof(kernel));
			kernels[num_kernels - 1].x = mouseX;
			kernels[num_kernels - 1].y = mouseY;
			kernels[num_kernels - 1].type = 2;
			/*printf("First num kernels %i ", num_kernels);
			int size = 1;
			num_kernels += size;
			kernels = (kernel*)realloc(kernels, num_kernels * sizeof(kernel));
			printf("num kernels %i ", num_kernels);
			for (int i = 0; i < size; i++) {
				int index = (num_kernels - 1) + i;
				kernels[index].x = mouseX+i;
				kernels[index].y = mouseY+i;
				kernels[index].type = 2;

			}*/

			//pixels[mouseY * width + mouseX] = 255;
		}
		/*
		switch (e.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT)
				leftMouseButtonDown = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)
				leftMouseButtonDown = true;
		case SDL_MOUSEMOTION:
			if (leftMouseButtonDown)
			{
				int mouseX = e.motion.x;
				int mouseY = e.motion.y;
				pixels[mouseY * width + mouseX] = 255;
				
			}
			break;
		}
		*/
		
			
		
		for (int i = 0; i < num_kernels; i++) {
			int x = kernels[i].x;
			int y = kernels[i].y;
			
			const unsigned int offset = (y * width + x);
			
			
			//printf("%zu", c);
			int ran = rand() & 1;			
			int r = ran == 0 ? -1 : 1;
			int l = ran == 1 ? -1 : 1;
			//printf(" ||ran %i:%i = %i || ", ran, r, l);
			Uint32 c = 0;
			if (kernels[i].type == 2) {
				
				c = pixels[offset + width]; //y+1
				if ((c == 0) || (c == 51200)) {
					if (kernels[i].y < (height - 1))
						kernels[i].y++;
				}
				else if ((pixels[offset + width - 1] == 0) || (pixels[offset + width + r] == 200)) {
					if ((kernels[i].x > 0) && (kernels[i].x < (width - 1)))
						kernels[i].x+=r;
					if (kernels[i].y < (height - 1))
						kernels[i].y++;
				}
				else if ((pixels[offset + width + 1] == 0) || (pixels[offset + width + l] == 200)) {
					if ((kernels[i].x > 0) && (kernels[i].x < (width - 1)))
						kernels[i].x+=l;
					if (kernels[i].y < (height - 1))
						kernels[i].y++;
				}

			}
			if (kernels[i].type == 1) {
				

				//printf(" %i", offset);
				c = pixels[offset + width]; //x+1 y+ 1
			

				if (pixels[offset + width] == 0) {
					if (kernels[i].y < height)
						kernels[i].y++;
				}
				else if (pixels[offset] == 51200) {
					if (kernels[i].y > 0)
						kernels[i].y--;
				}
				else if (pixels[offset - width] == 51200) {
					if (kernels[i].y > 0)
						kernels[i].y-=2;
				}
				else if (pixels[offset + width - 1] == 0) // x-1 y+1 
				{
					if (kernels[i].y < height)
						kernels[i].y++;
					if (kernels[i].x > 0)
						kernels[i].x--;
				

				}
				else if (pixels[offset + width + 1] == 0) // x+1 y01
				{
					if (kernels[i].y < height)
						kernels[i].y++;
					if (kernels[i].x < width)
						kernels[i].x++;				

				}
				else if (pixels[offset + r] == 0) {
					if ((kernels[i].x < width) && (kernels[i].x > 0))
						kernels[i].x += r;
				}
				else if (pixels[offset + l] == 0) {
					if (c == 0) {
						if ((kernels[i].x < width) && (kernels[i].x > 0))
							kernels[i].x += l;
					}

				}
			}
		}
		memset(pixels, 0, width * height * sizeof(Uint32));

		for (int i = 0; i < num_kernels; i++) {
			int x = kernels[i].x;
			int y = kernels[i].y;
			const unsigned int offset = (y * width + x);
			if (kernels[i].type == 1)
				pixels[offset + 0] = 200;        
			if (kernels[i].type == 2)
				pixels[offset + 0] = 200 << 16;        // 51200

		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);


		frames++;
		const Uint64 end = SDL_GetPerformanceCounter();
		const static Uint64 freq = SDL_GetPerformanceFrequency();
		const double seconds = (end - start) / static_cast<double>(freq);
		if (seconds > 2.0)
		{
			printf(" frames in \n");
			printf("seconds %f \n ", seconds);
			printf("FPS %f \n", frames / seconds);
			printf("num_kernels %i \n", num_kernels);			
			start = end;
			frames = 0;
		}

	}

	delete[] pixels;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
