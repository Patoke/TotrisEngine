#pragma once

class CRenderer {
public:
	SDL_Renderer* m_pRenderer;

	void SetRenderColor(Color col) {
		SDL_SetRenderDrawColor(m_pRenderer, col.r, col.g, col.b, col.a);
	}

	void DrawRect(SDL_Rect rect, Color col) {
		SetRenderColor(col);
		SDL_RenderDrawRect(m_pRenderer, &rect);
	}

	void DrawRectFilled(SDL_Rect rect, Color col) {
		SetRenderColor(col);
		SDL_RenderFillRect(m_pRenderer, &rect);
	}

	void DrawLine(SVec2 from, SVec2 to, Color col) {
		SetRenderColor(col);
		SDL_RenderDrawLine(m_pRenderer, from.x, from.y, to.x, to.y);
	}
};

class CWindow : public CRenderer {
private:
	bool m_bExit;
	SDL_Window* m_pWindow;

public:
	constexpr bool HasToExit() { return m_bExit; }

	CWindow(const char* window_name, SDL_Rect window_data) : m_bExit(false) {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			assert(true);

		m_pWindow = SDL_CreateWindow(window_name, window_data.x, window_data.y, window_data.w, window_data.h, 0);

		uint32_t renderFlags = SDL_RENDERER_ACCELERATED;

		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, renderFlags);
	}

	void Destroy() {
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
	}

	void RunInput(std::function<void(SDL_Event)> on_input) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: m_bExit = true; break; 
			}

			on_input(event);
        }
	}
	
	void CreateFrame() {
		SDL_RenderClear(m_pRenderer);
	}

	void RenderFrame() {
		SDL_RenderPresent(m_pRenderer);

		// calculates to 60 fps
		SDL_Delay(1000 / 60);
	}
};

extern std::shared_ptr<CWindow> g_pWindow;