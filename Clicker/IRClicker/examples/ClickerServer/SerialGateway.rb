#!/usr/bin/env ruby

require 'rubygems'
require 'serialport'

class SerialGateway
  def initialize ( port_dev, baud_rate )
    begin
      #@sp = SerialPort.new( port_dev, baud_rate, data_bits, stop_bits, parity )
      @sp = SerialPort.new( port_dev, baud_rate )
      at_exit { do_at_exit() }
    rescue => e
      puts "Cannot initialise serial communication on #{port_dev} @ #{baud_rate}"
    end
    @mux = Mutex.new
  end

  def send ( command )
    @mux.synchronize do
      @sp.puts command
    end
  end
end

# Debugging
puts 'hello (serial/arduino) world'
#port_dev = '/dev/ttyACM0'
port_dev = '/dev/ttyUSB0'
baud_rate = 115200
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE

sg = SerialGateway.new( port_dev, baud_rate )
while true do
  print '? '
  command = gets.chomp
  puts "-sending- #{command}"
  sg.send command
end
