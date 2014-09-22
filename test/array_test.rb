require 'test_helper'

class AmsMathTex2MMLArrayTest < MiniTest::Test
  def setup
    @itex = Itex2MML::Parser.new
  end

  def write_to_test_file(converted)
    outfile = """
    <html>

    <body>

    #{converted}

    </math>

    </body>

    </html>
    """

    File.open("test.html", "w") { |f| f.write(outfile) }
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
end
