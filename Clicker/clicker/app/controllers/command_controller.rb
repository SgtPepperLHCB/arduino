class CommandController < ApplicationController
  
  def command
    @result = params[ :command ]
    #@result = params[ :id ]
    logger.debug "---LOG command|#{@result}|"
    SerialGatewayService.instance.send @result
  end #-command

end #-CommandController
