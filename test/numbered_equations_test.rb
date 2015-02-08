require 'test_helper'

class Mtex2MMLTest < MiniTest::Test

  def setup
    @mtex = Mtex2MML::Parser.new
  end

  def test_single_equation
    text = fixture_file('numbered_equations', 'single_equation', '.tex')
    write_to_test_file @mtex.filter(text)
    assert_equal(@mtex.filter(text), fixture_file('numbered_equations', 'single_equation'))
  end
end
