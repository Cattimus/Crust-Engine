mod sdl_bindings;

mod sdl;
use sdl::*;

use std::rc::*;

fn main() {
	crust_init();
	let mut window = CrustWindow::new("Test window", 800, 600);

	//create texture and make an Rc for passing to objects
	let texture = CrustTexture::new(&window, "media/test.png");
	let tex_ref = Rc::new(texture);

	let mut obj = CrustObject::new(150, 150, &tex_ref);
	obj.y = 250;

	crust_renderclear(&window);
	obj.render(&window);
	crust_renderpresent(&window);

	std::thread::sleep(std::time::Duration::from_secs(5));
	window.destroy();
	crust_exit();
}
