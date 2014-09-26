require 'test_helper'

class AmsMathTex2MMLArrayTest < MiniTest::Test

  def setup
    @itex = Itex2MML::Parser.new
  end

  def test_ex_spacing
    text = '''
$$
f(n) =
\begin{cases}
\frac{n}{2},  & \text{if n is even} \\\\[20ex]
3n+1, & \text{if n is odd}
\end{cases}
$$
'''

    write_to_test_file @itex.filter(text)
    assert_equal(@itex.filter(text), fixture_file("ex_spacing"))
  end
end
