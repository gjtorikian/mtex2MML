require 'test_helper'

class Mtex2MMLTest < MiniTest::Test

  def setup
    @mtex = Mtex2MML::Parser.new
  end

  def test_single_equation
    text = fixture_file('numbered_equations', 'single_equation', '.tex')
    assert_equal(@mtex.filter(text), fixture_file('numbered_equations', 'single_equation'))
  end

  def test_multiple_equations
    text = fixture_file('numbered_equations', 'multiple_equations', '.tex')
    assert_equal(@mtex.filter(text), fixture_file('numbered_equations', 'multiple_equations'))
  end
end
