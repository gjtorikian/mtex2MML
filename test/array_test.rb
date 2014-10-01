require 'test_helper'

class AmsMathTex2MMLArrayTest < MiniTest::Test

  def setup
    @itex = Itex2MML::Parser.new
  end

  def test_basic_array
    text = '''
$$
\begin{array}{cc}
Bad & Good
\end{array}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("basic_array"))
  end

  def test_array_with_hline
    text = '''
$$
\begin{array}{clcr}
n & \text{Left} & \text{Center} & \text{Right} \\\\
\hline
1 & 0.24 & 1 & 125 \\\\
2 & -1 & 189 & -8 \\\\
3 & -20 & 2000 & 1+10i
\end{array}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("array_with_hline"))
  end

  def test_array_with_hline_and_hdashline
    text = '''
$$
\begin{array}{clcr}
n & \text{Left} & \text{Center} & \text{Right} \\\\
\hline
1 & 0.24 & 1 & 125 \\\\
2 & -1 & 189 & -8 \\\\
\hdashline
3 & -20 & 2000 & 1+10i
\end{array}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("array_with_hline_and_hdashline"))
  end

  def test_array_pos_alignment
    text = '''
$$
\begin{array}[t]{clcr}
n & \text{Left} & \text{Center} & \text{Right} \\\\
1 & 0.24 & 1 & 125 \\\\
2 & -1 & 189 & -8 \\\\
3 & -20 & 2000 & 1+10i
\end{array}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("array_pos_alignment"))
  end

  def test_array_pos_alignment_with_hline
    text = '''
$$
\begin{array}[t]{clcr}
n & \text{Left} & \text{Center} & \text{Right} \\\\
\hline
1 & 0.24 & 1 & 125 \\\\
\hline
2 & -1 & 189 & -8 \\\\
\hline
3 & -20 & 2000 & 1+10i
\hline
\end{array}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("array_pos_alignment_with_hline"))
  end

  def test_array_vertical_column
    text = '''
$$
\begin{array}{c|c}
Bad & Good
\end{array}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("array_vertical_column"))
  end

  def test_array_vertical_column_with_align
    text = '''
$$
\begin{array}[b]{:c:c}
Bad & Good
\end{array}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("array_vertical_column_with_align"))
  end

  def test_array_with_vertical_and_horizontal_dashes

text = '''
$$
\begin{array}{:c:cc:c:}
\hdashline
1 & 2 & 3 & 4\\\\
\hdashline
4 & 5 & 6 & 7\\\\
\hdashline
7 & 8 & 9 & 10
\end{array}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("array_with_vertical_and_horizontal_dashes"))
  end

  def test_array_nesting

  text = '''
$$
\begin{array}{c}
  \begin{array}{c:c}
    \begin{array}{c|cclc}
      \text{min} & 0 & 1 & 2 & 3\\\\
      \hline
      0 & 0 & 0 & 0 & 0\\\\
      1 & 0 & 1 & 1 & 1\\\\
      2 & 0 & 1 & 2 & 2\\\\
      3 & 0 & 1 & 2 & 3
    \end{array}
  &
    \begin{array}{c|cccl}
      \text{max}&0&1&2&3\\\\
      \hline
      0 & 0 & 1 & 2 & 3\\\\
      1 & 1 & 1 & 2 & 3\\\\
      2 & 2 & 2 & 2 & 3\\\\
      3 & 3 & 3 & 3 & 3
    \end{array}
  \end{array}
\\\\
  \begin{array}{l|cccc}
    \Delta&0&1&2&3\\\\
    \hline
    0 & 0 & 1 & 2 & 3\\\\
    1 & 1 & 0 & 1 & 2\\\\
    2 & 2 & 1 & 0 & 1\\\\
    3 & 3 & 2 & 1 & 0
  \end{array}
\end{array}
$$
'''

    assert_equal(@itex.filter(text), fixture_file("array_nesting"))
  end

  def test_strip_excess_whitespace_in_array_attributes

    text = '''
$$
\begin{array}{c|c}
\mathrm{Bad} & \mathrm{Better} \\\\
\hline \\\\
\iiint_V f(x)dz dy dx & \iiint_V f(x)\,dz\,dy\,dx
\end{array}
$$
  '''

    assert_equal(@itex.filter(text), fixture_file("strip_excess_whitespace_in_array_attributes"))
  end

  def test_augmented_matrix

    text = '''
$$ \left[
    \begin{array}{cc|c}
      1&2&3\\\\
      4&5&6
    \end{array}
\right] $$
    '''

    assert_equal(@itex.filter(text), fixture_file("augmented_matrix"))
  end
end
