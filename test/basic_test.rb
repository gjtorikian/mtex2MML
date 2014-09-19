require 'test_helper'

class Itex2MMLTest < MiniTest::Unit::TestCase

  def test_inline_html
    itex = Itex2MML::Parser.new
    assert_equal("Inline: <math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", itex.html_filter('Inline: $\sin(x)$'))
  end

  def test_inline
    itex = Itex2MML::Parser.new
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", itex.filter('Inline: $\sin(x)$'))
  end

  def test_inline_inline
    itex = Itex2MML::Parser.new
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", itex.inline_filter('\sin(x)'))
  end

  def test_block_html
    itex = Itex2MML::Parser.new
    assert_equal("Block: <math xmlns='http://www.w3.org/1998/Math/MathML' display='block'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", itex.html_filter('Block: $$\sin(x)$$'))
  end

  def test_block
    itex = Itex2MML::Parser.new
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='block'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", itex.filter('Block: $$\sin(x)$$'))
  end

  def test_block_block
    itex = Itex2MML::Parser.new
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='block'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", itex.block_filter('\sin(x)'))
  end

  def test_inline_utf8
    itex = Itex2MML::Parser.new
    s = "".respond_to?(:force_encoding) ? "\u00F3" : "\303\263"
    assert_equal("ecuasi"+ s + "n <math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'>" +
           "<semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>",
            itex.html_filter("ecuasi\303\263n $\\sin(x)$"))
  end

  def test_inline_utf8_inline
    itex = Itex2MML::Parser.new
    assert_equal("<math xmlns='http://www.w3.org/1998/Math/MathML' display='inline'><semantics><mrow><mi>sin</mi><mo stretchy=\"false\">(</mo><mi>x</mi><mo stretchy=\"false\">)</mo></mrow><annotation encoding='application/x-tex'>\\sin(x)</annotation></semantics></math>", itex.filter("ecuasi\303\263n $\\sin(x)$"))
  end

  def test_utf8_in_svg_foreignObject
    itex = Itex2MML::Parser.new
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
      itex.filter("$g' = \\begin{svg}<svg width='40' height='40' xmlns='http://www.w3.org/20" +
        "00/svg' xmlns:xlink='http://www.w3.org/1999/xlink'><foreignObject height='19' width='" +
        "20' font-size='16' y='0' x='0'><math display='inline' xmlns='http://www.w3.org/1998/M" +
        "ath/MathML'><mi>g</mi><mo>\342\200\262</mo></math></foreignObject></svg>\\end{svg}$"))
  end

end
