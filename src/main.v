module main

import vweb

struct App {
    vweb.Context
}

fn main() {
    vweb.run_at(new_app(), vweb.RunParams{
        port: 8081
    }) or { panic(err) }
}

fn new_app() &App {
    mut app := &App{}
    return app
}

['/']
pub fn (mut app App) le_root() vweb.Result {
	return app.page_logo('000000')
}

fn hex_letters(str string) bool {
	return str.contains_only('1234567890abcdefABCDEF')
}
fn all_letters(str string) bool {
	return str.contains_only('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')
}

['/:color']
pub fn (mut app App) page_logo(color string) vweb.Result {
	mut color_hex := ''

	if (color.len_utf8() == 3 || color.len_utf8() == 6) && hex_letters(color) {
		color_hex = '#$color'
	} else if color == 'zeus' {
		color_hex = '#ff7f00'
	} else if all_letters(color) {
		color_hex = color
	} else {
		color_hex = '#000000'
	}

	app.add_header('Content-type', 'image/svg+xml')

    return $vweb.html()
}
