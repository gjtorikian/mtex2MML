require 'test_helper'

class AmsMathTex2MMLEnvTest < MiniTest::Test

  def setup
    @itex = Itex2MML::Parser.new
  end

  def test_matrix_ex_spacing
    text = '''
$$
\left\{
  \begin{matrix} 1 & 2 & 3 \\\\[40ex]
4 & 5 & 6
\end{matrix}
\right)
$$
'''

    assert_equal(@itex.filter(text), fixture_file("matrix_ex_spacing"))
  end

  def test_matrix_no_ex_spacing
    text = '''
$$
\left\{
  \begin{matrix} 1 & 2 & 3 \\\\
4 & 5 & 6
\end{matrix}
\right)
$$
'''

    assert_equal(@itex.filter(text), fixture_file("matrix_no_ex_spacing"))
  end

  def test_matrix_no_lines
    text = '''
$$
\left\{
  \begin{matrix} 1 & 2 & 3
\end{matrix}
\right)
$$
'''

    assert_equal(@itex.filter(text), fixture_file("matrix_no_lines"))
  end

  def test_gathered_ex_spacing
    text = '''
$$
\begin{gathered}
2x - 5y =  8 \\\\[2pt]
3x^2 + 9y =  3a + c
\end{gathered}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("gathered_ex_spacing"))
  end

  def test_gathered_no_ex_spacing
    text = '''
$$
\begin{gathered}
2x - 5y =  8 \\\\
3x^2 + 9y =  3a + c
\end{gathered}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("gathered_no_ex_spacing"))
  end

  def test_gathered_no_lines
    text = '''
$$
\begin{gathered}
3x^2 + 9y =  3a + c
\end{gathered}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("gathered_no_lines"))
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

  def test_cases_no_ex_spacing
    text = '''
$$
f(n) =
\begin{cases}
\frac{n}{2},  & \text{if n is even} \\\\
3n+1, & \text{if n is odd}
\end{cases}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("cases_no_ex_spacing"))
  end

  def test_cases_no_lines
    text = '''
$$
f(n) =
\begin{cases}
\frac{n}{2},  & \text{if n is even}
\end{cases}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("cases_no_lines"))
  end
end
