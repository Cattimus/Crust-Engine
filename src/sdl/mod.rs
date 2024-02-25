#![allow(dead_code)]

pub mod window;
pub use window::*;

pub mod texture;
pub use texture::*;

pub mod object;
pub use object::*;

use crate::sdl_bindings::*;

use std::ffi::*;

pub fn crust_init() -> bool {
	unsafe {
		//init SDL
		if SDL_Init(SDL_INIT_VIDEO) < 0 {
			eprintln!("Unable to initialize SDL");
			return false;
		}

		if IMG_Init(IMG_InitFlags_IMG_INIT_PNG) != IMG_InitFlags_IMG_INIT_PNG {
			eprintln!("Unable to initialize SDL_Image");
			SDL_Quit();
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
		IMG_Quit();
		SDL_Quit();
	}
}

pub fn crust_renderclear(window: &CrustWindow) {
	unsafe {
		SDL_RenderClear(window.renderer);
	}
}

pub fn crust_renderpresent(window: &CrustWindow) {
	unsafe {
		SDL_RenderPresent(window.renderer);
	}
}