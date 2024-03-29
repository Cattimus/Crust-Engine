use std::ptr::*;
use std::ffi::*;

use crate::sdl_bindings::*;

pub struct CrustWindow {
	pub(super) window: *mut SDL_Window,
	pub(super) renderer: *mut SDL_Renderer,
	pub w: i32,
	pub h: i32,
	pub x: i32,
	pub y: i32
}

impl CrustWindow {
	pub fn new(title: &str, w: i32, h: i32) -> Self {
		unsafe {
			let title = CString::new(title).unwrap();
			let window = SDL_CreateWindow(
				title.as_ptr(),
				SDL_WINDOWPOS_CENTERED_MASK as i32,
				SDL_WINDOWPOS_CENTERED_MASK as i32,
				w,
				h,
				SDL_WindowFlags_SDL_WINDOW_SHOWN as u32
			);

			let mut renderer: *mut SDL_Renderer = null_mut();
			if window.is_null() {
				eprintln!("Error in creating SDL window");
			}
			else {
				renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags_SDL_RENDERER_ACCELERATED as u32);
			}

			if renderer.is_null() {
				eprintln!("Error in creating SDL_Renderer");
			}

			//get position of created window
			let mut window_x = 0;
			let mut window_y = 0;
			SDL_GetWindowPosition(window, &mut window_x, &mut window_y);

			CrustWindow {
				window: window,
				renderer: renderer,
				w,
				h,
				x: window_x,
				y: window_y
			}
		}
	}

	//determine if window is valid or not
	pub fn is_valid(&self) -> bool {
		return !self.window.is_null();
	}

	//reclaim window resources
	pub fn destroy(&mut self) {
		if self.is_valid() {
			unsafe {
				SDL_DestroyWindow(self.window);
				self.window = null_mut();
			}
		}
	}
}