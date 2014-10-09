folder_path = "/Users/garentorikian/Development/mtex2MML/test/fixtures/MathJax/LaTeXToMathML-tex"
Dir.glob("**/*.tex").sort.each do |f|
  filename = File.basename(f, File.extname(f))
  File.rename(f, File.join(File.dirname(f), filename + ".xtex"))
end