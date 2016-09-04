require 'sinatra'
require 'base64'

Tilt.register Tilt::ERBTemplate, 'svg'

get '/:file' do
  headers 'Content-Type' => 'image/svg+xml'

  c = params['color']
  css = "path, rect { fill: #{c} !important; stroke: #{c} !important }"
  encoded_css = Base64.encode64(css)
  style = %(<?xml-stylesheet type="text/css" href="data:text/css;charset=utf-8;base64,#{encoded_css}" ?>)

  f = File.read("images/#{params['file']}").lines
  f[0] + style + f[1..-1].join
end
