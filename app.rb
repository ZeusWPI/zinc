# frozen_string_literal: true

require 'sinatra'

configure do
  @@LOGO_PRE, @@LOGO_POST = File.read('images/zeuslogo.svg').split('$COLOR')
end

get '/:color?' do
  headers 'Content-Type' => 'image/svg+xml'
  color = if params[:color] == 'zeus'
            '#ff7f00'
          elsif /^([0-9a-fA-F]{3}|[0-9a-fA-F]{6})$/.match?(params[:color])
            '#' + params[:color]
          elsif /^[a-zA-Z]+$/.match?(params[:color])
            params[:color]
          else
            '#000000'
          end

  String.new.concat(@@LOGO_PRE, color, @@LOGO_POST)
end
