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

    assert_equal(@mtex.filter(text), fixture_file("cornercases", "broken_up_inline_env"))
  end

  def test_some_crazy_alignment
    text = '''
$$
\begin{aligned}
    (L_{ijr}^{T}L_{ijr}+\left[\begin{array}{cc}q_{11} & 0\\\\0 & 0 \end{array}\right])\mathbf{v}_{er,x}
    +\left[\begin{array}{cc}q_{12} & 0\\\\0 & 0 \end{array}\right]\mathbf{v}_{er,y}
    +\left[\begin{array}{cc}q_{13} & 0\\\\0 & 0 \end{array}\right]\mathbf{v}_{er,z}
    +\left[\begin{array}{c}v_{e,g}q_{14}+q_{15}\\\\0\end{array}\right]
    +L_{ijr}^{T}b_{x} = 0 \\\\
    \left[\begin{array}{cc}q_{12} & 0\\\\0 & 0\end{array}\right]\mathbf{v}_{er,x}
    +(L_{ijr}^{T}L_{ijr}+\left[\begin{array}{cc}q_{22} & 0\\\\0 & 0\end{array}\right])\mathbf{v}_{er,y}
    +\left[\begin{array}{cc}q_{23} & 0\\\\0 & 0\end{array}\right]\mathbf{v}_{er,z}
    +\left[\begin{array}{c}v_{e,g}q_{24}+q_{25}\\\\0\end{array}\right]
    +L_{ijr}^{T}b_{y} = 0 \\\\
    \left[\begin{array}{cc}q_{13} & 0\\\\0 & 0\end{array}\right]\mathbf{v}_{er,x}
    +\left[\begin{array}{cc}q_{23} & 0\\\\0 & 0\end{array}\right]\mathbf{v}_{er,y}
    +(L_{ijr}^{T}L_{ijr}+\left[\begin{array}{cc}q_{33} & 0\\\\0 & 0\end{array}\right])\mathbf{v}_{er,z}
    +\left[\begin{array}{c}v_{e,g}q_{34}+q_{35}\\\\0\end{array}\right]
    +L_{ijr}^{T}b_{z} = 0 \\\\
    \left[\begin{array}{cc}q_{14} & 0\end{array}\right]\mathbf{v}_{er,x}
    +\left[\begin{array}{cc}q_{24} & 0\end{array}\right]\mathbf{v}_{er,y}
    +\left[\begin{array}{cc}q_{34} & 0\end{array}\right]\mathbf{v}_{er,z}
    +q_{44}v_{e,g}
    +q_{45} = 0
\end{aligned}
$$
'''

    assert_equal(@mtex.filter(text), fixture_file("cornercases", "some_crazy_alignment"))
  end

  def test_chained_monstrosity
    str_start = '$\Huge '
    str_end = '$'
    blob = '\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}'
    text = str_start + blob + str_end

    assert_equal(@mtex.filter(text), fixture_file("cornercases", "chained_monstrosity"))

    # just a few more sqrts and it blows up
    text = str_start + '\sqrt\sqrt\sqrt\sqrt\sqrt\sqrt' + blob + '}}}}}}' + str_end

    # doing this in a fork because otherwise it really screws up the test runner
    p = Proc.new do
      @mtex.filter(text)
    end
    fork do
      assert_raises Mtex2MML::Error do
        p.call
      end
    end
  end
end
