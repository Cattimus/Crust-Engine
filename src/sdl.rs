#![allow(dead_code)]

mod sdl_bindings;
use sdl_bindings::*;

use std::ffi::*;
use std::ptr::*;

pub fn crust_init() -> bool {
	unsafe {
		//init SDL
		if SDL_Init(SDL_INIT_VIDEO) < 0 {
			eprintln!("Unable to initialize SDL");
			return false;
		}

		//set render scale to nearest neighbor
		let value = CString::new("0").unwrap();
		let hint = SDL_HINT_RENDER_SCALE_QUALITY.as_ptr() as *const c_char;
		if SDL_SetHint(hint, value.as_ptr()) == 0 {
			eprintln!("Unable to set billinear rendering");
		}

		//set vsync to on
		let value = CString::new("1").unwrap();
		let hint = SDL_HINT_RENDER_VSYNC.as_ptr() as *const c_char;
		if SDL_SetHint(hint, value.as_ptr()) == 0 {
			eprintln!("Unable to set vsync");
		}

		return true;
	}

}

pub fn crust_exit() {
	unsafe {
		SDL_Quit();
	}
}

pub struct CrustWindow {
	window: *mut SDL_Window,
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

			if window.is_null() {
				eprintln!("Error in creating SDL window");
			}

			//get position of created window
			let mut window_x = 0;
			let mut window_y = 0;
			SDL_GetWindowPosition(window, &mut window_x, &mut window_y);

			CrustWindow {
				window: null_mut(),
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