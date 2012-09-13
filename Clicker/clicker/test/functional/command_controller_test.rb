require 'test_helper'

class CommandControllerTest < ActionController::TestCase
  test "should get command" do
    get :command
    assert_response :success
  end

end
