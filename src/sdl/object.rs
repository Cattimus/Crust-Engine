use std::ptr::*;

use crate::sdl_bindings::*;
use crate::sdl::window::*;
use crate::sdl::texture::*;

use std::rc::*;

pub struct CrustObject {
	pub texture: Rc<CrustTexture>,
	pub x: i32,
	pub y: i32,
	pub w: i32,
	pub h: i32
}

impl CrustObject {
	pub fn new(w: i32, h: i32, tex: &Rc<CrustTexture>) -> Self {
		CrustObject {
			texture: Rc::clone(tex),
			x: 0,
			y: 0,
			w: w,
			h: h
		}
	}

	pub fn render(&self, window: &CrustWindow) {
		unsafe {
			let mut obj_pos = SDL_Rect {
				x: self.x,
				y: self.y,
				w: self.w,
				h: self.h
			};

			SDL_RenderCopy(window.renderer, (*self.texture).texture, null_mut(), &mut obj_pos);
		}
	}
}