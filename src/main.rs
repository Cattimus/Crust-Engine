mod sdl_bindings;

mod sdl;
use sdl::*;

fn main() {
	crust_init();
	let mut window = CrustWindow::new("Test window", 800, 600);
	std::thread::sleep(std::time::Duration::from_secs(5));
	window.destroy();
	crust_exit();
}
