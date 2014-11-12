require 'test_helper'

class Mtex2MMLTest < MiniTest::Test

  def setup
    @mtex = Mtex2MML::Parser.new
  end

  def test_max_limits_
    text = '$\max\limits_{1\leq j\leq n}$'
    assert_equal(@mtex.filter(text), fixture_file("functions", "max_limits_"))
  end

  def test_min_limits_
    text = '$\min\limits_{1\leq j\leq n}$'
    assert_equal(@mtex.filter(text), fixture_file("functions", "min_limits_"))
  end
end
