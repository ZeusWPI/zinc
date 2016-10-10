require 'sinatra'
require 'base64'

get '/:file' do
  headers 'Content-Type' => 'image/svg+xml'
  c = 'black'
  c = params['color'] if params['color']
  File.read("images/#{params['file']}").gsub('$COLOR', c)
end
