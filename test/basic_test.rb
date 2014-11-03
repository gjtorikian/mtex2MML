require 'test_helper'

class Mtex2MMLTest < MiniTest::Test

  def setup
    @mtex = Mtex2MML::Parser.new
  end

  def test_inline_html
    assert_equal("Inline: <math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", @mtex.html_filter('Inline: $\sin(x)$'))
  end

  def test_inline
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", @mtex.filter('Inline: $\sin(x)$'))
  end

  def test_inline_inline
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", @mtex.inline_filter('\sin(x)'))
  end

  def test_block_html
    assert_equal("Block: <math xmlns='http://www.w3.org/1998/Math/MathML' display='block'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", @mtex.html_filter('Block: $$\sin(x)$$'))
  end

  def test_block
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='block'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", @mtex.filter('Block: $$\sin(x)$$'))
  end

  def test_block_block
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='block'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", @mtex.block_filter('\sin(x)'))
  end

  def test_inline_utf8
    s = "".respond_to?(:force_encoding) ? "\u00F3" : "\303\263"
    assert_equal("ecuasi"+ s + "n <math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'>" +
           "<semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>",
            @mtex.html_filter("ecuasi\303\263n $\\sin(x)$"))
  end

  def test_inline_utf8_inline
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", @mtex.filter("ecuasi\303\263n $\\sin(x)$"))
  end

  def test_utf8_in_svg_foreignObject
    s = "".respond_to?(:force_encoding) ? "\u2032" : "\342\200\262"
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'><semantics><mrow><mi>g" +
        "</mi><mo>&prime;</mo><mo>=</mo><semantics><annotation-xml encoding=\"SVG1.1\"><svg w" +
        "idth='40' height='40' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3." +
        "org/1999/xlink'><foreignObject height='19' width='20' font-size='16' y='0' x='0'><ma" +
        "th display='inline' xmlns='http://www.w3.org/1998/Math/MathML'><mi>g</mi><mo>" +
        s + "</mo></math></foreignObject></svg></annotation-xml></semantics></mrow><annotation encoding='application/x-tex'>" +
        "g&apos; = \\begin{svg}&lt;svg width=&apos;40&apos; height=&apos;40&apos; xmlns=&apos;http://www.w3.org/2000/svg&apos; " +
        "xmlns:xlink=&apos;http://www.w3.org/1999/xlink&apos;&gt;&lt;foreignObject height=&apos;19&apos; width=&apos;20&apos; " +
        "font&#x2d;size=&apos;16&apos; y=&apos;0&apos; x=&apos;0&apos;&gt;&lt;math display=&apos;inline&apos; " +
        "xmlns=&apos;http://www.w3.org/1998/Math/MathML&apos;&gt;&lt;mi&gt;g&lt;/mi&gt;&lt;mo&gt;′&lt;/mo&gt;&lt;/math&gt;&lt;/foreignObject&gt;&lt;/svg&gt;\\end{svg}</annotation></semantics></math>",
      @mtex.filter("$g' = \\begin{svg}<svg width='40' height='40' xmlns='http://www.w3.org/20" +
        "00/svg' xmlns:xlink='http://www.w3.org/1999/xlink'><foreignObject height='19' width='" +
        "20' font-size='16' y='0' x='0'><math display='inline' xmlns='http://www.w3.org/1998/M" +
        "ath/MathML'><mi>g</mi><mo>\342\200\262</mo></math></foreignObject></svg>\\end{svg}$"))
  end

  def test_comments_are_ignored

    text = '''
$$
\begin{array}{cc}
% A comment!
Bad & Good
\end{array}
$$
'''

    assert_equal(@mtex.filter(text), fixture_file("basic", "comments_are_ignored"))
  end
end
