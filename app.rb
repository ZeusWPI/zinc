# frozen_string_literal: true

require 'sinatra'

get '/:color?' do
  headers 'Content-Type' => 'image/svg+xml'
  color = if params[:color] == 'zeus'
            '#ff7f00'
          elsif /^([0-9a-fA-F]{3}|[0-9a-fA-F]{6})$/ =~ params[:color]
            '#' + params[:color]
          elsif /^[a-zA-Z]+$/ =~ params[:color]
            params[:color]
          else
            '#000000'
          end
  File.read('images/zeuslogo.svg').gsub('$COLOR', color)
end

