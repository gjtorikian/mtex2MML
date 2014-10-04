require 'test_helper'

class Mtex2MMLCornerCasesTest < MiniTest::Test

  def setup
    @mtex = Mtex2MML::Parser.new
  end

  def test_broken_up_inline_env
    text = '''
$g\'_{\tau} = \left(
\begin{smallmatrix}1&u\\\\0&1\end{smallmatrix} \right) \left(
\begin{smallmatrix}v^{1/2}&0\\\\0&v^{-1/2}\end{smallmatrix} \right)$
'''

    assert_equal(@mtex.filter(text), fixture_file("broken_up_inline_env"))
  end

end
