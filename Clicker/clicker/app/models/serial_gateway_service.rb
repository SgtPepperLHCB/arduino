#!/usr/bin/env ruby

require 'rubygems'
require 'serialport'

class SerialGatewayService
  @@instance = nil
  
  def self.instance
    @@instance || @@instance = self.new
  end
  
  def initialize
    puts "***sgs init"
    begin
      #@sp = SerialPort.new( port_dev, baud_rate, data_bits, stop_bits, parity )
      @sp = SerialPort.new( '/dev/ttyUSB0', 115200 )
      #at_exit { do_at_exit() }
    rescue => e
      puts "Cannot initialise serial communication on #{port_dev} @ #{baud_rate}"
    end
    @mux = Mutex.new
  end

  def send command
    @mux.synchronize do
      @sp.puts command
    end
  end

end #-SerialGatewayService
