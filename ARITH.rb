#!/usr/bin/env ruby
n = gets.chomp.to_i

inputs = []
n.times{|x| inputs << gets.chomp}

inputs.each do |str|
	exp = str.split(/\*|\+|\-/)
	lhs = exp.first.to_i
	rhs = exp.last.to_i
	op = str[str =~ /\*|\+|\-/]
	
	l_len = lhs.to_s.length
	r_len = rhs.to_s.length
	
	len = [(lhs+rhs).to_s.length, lhs.to_s.length+1, rhs.to_s.length+1].max
	case op
	when "+"
		puts "#{format("%#{len}i", lhs)}\n+#{format("%#{len-1}i",rhs)}"
		puts "-"*len
		puts "#{format("%#{len}i", lhs+rhs)}"
	when "-"
		puts "#{format("%#{len}i", lhs)}\n-#{format("%#{len-1}i",rhs)}"
		puts "-"*len
		puts "#{format("%#{len}i", lhs-rhs)}"
	when "*"
		puts "#{format("%#{len}i", lhs)}\n*#{format("%#{len-1}i",rhs)}"
		
	end
	
	puts ""
	
end


