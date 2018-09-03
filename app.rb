require 'sinatra'
require 'base64'

get '/:color' do
  headers 'Content-Type' => 'image/svg+xml'
  c = 'black'
  c = params['color'] if params['color'] and !params['color'].match(/\A[a-zA-Z0-9]*\z/).nil?
  File.read("images/zeuslogo.svg").gsub('$COLOR', c)
end

get '/?' do
  headers 'Content-Type' => 'image/svg+xml'
  File.read("images/zeuslogo.svg").gsub('$COLOR', 'black')
end

