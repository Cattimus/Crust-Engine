use std::ffi::*;

use crate::sdl_bindings::*;
use crate::sdl::window::*;

pub struct CrustTexture {
	pub(super) texture: *mut SDL_Texture,
	pub(super) filename: String
}

impl CrustTexture {
	pub fn new(window: &CrustWindow, filepath: &str) -> Self {
		unsafe {
			let path = CString::new(filepath).unwrap();
			let texture = IMG_LoadTexture(window.renderer, path.as_ptr());
			if texture.is_null() {
				eprintln!("Error in creating texture from file: {}", filepath);
			}

			CrustTexture {
				texture: texture,
				filename: filepath.to_string() //theoretically copies the string
			}
		}
	}
}