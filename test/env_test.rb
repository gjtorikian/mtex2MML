# encoding: UTF-8
require 'test_helper'

class AmsMathTex2MMLEnvTest < MiniTest::Test

  def setup
    @itex = Itex2MML::Parser.new
  end

  def test_cases_ex_spacing
    text = '''
$$
f(n) =
\begin{cases}
\frac{n}{2},  & \text{if n is even} \\\\[20ex]
3n+1, & \text{if n is odd}
\end{cases}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("cases_ex_spacing"))
  end
end
