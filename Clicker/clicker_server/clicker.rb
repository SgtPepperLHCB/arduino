require 'rubygems'
require 'sinatra'
require './serial_gateway_service'

configure do
  set :symphonic, [
  'Power',
  'Sleep',
  'Eject',

  '1',
  '2',
  '3',
  'Return',

  '4',
  '5',
  '6',
  'Channel Up',

  '7',
  '8',
  '9',
  'Channel Dn',

  '0',
  '+100',
  'Volume Up',

  'Menu',
  'Display',
  'Mute',
  'Volumn Dn',

  '<- Rewind',
  '^  Play',
  '-> Fast Fwd',
  'v  Stop',

  'Record',
  'Speed',
  'Pause',

  'Clear/Reset',
  'Game',
  'Time Srch',
  ]
end

get '/' do
  logger.info '/:index.erb'
  erb :index
end

get '/symphonic' do
  logger.info '/symphonic/:symphonic.erb'
  @buttons = options.symphonic
  erb :symphonic
end
post '/symphonic' do
  logger.info "/symphonic/ POST #{request.POST.keys[0]}"
  #request.POST.each { |k, v| logger.info "#{k} = #{v}" }
  SerialGatewayService.instance.send request.POST.keys[0]
  @buttons = options.symphonic
  erb :symphonic
end

get '/clicker/*' do
  logger.info "/clicker #{params[:splat]}"
  params[:splat]
  SerialGatewayService.instance.send params[:splat]
end

