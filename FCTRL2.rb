#!/usr/bin/env ruby

fac = [1,1,2,6,24,120]

t = gets.chomp.to_i
t.times do |x|
	n = gets.chomp.to_i
	while fac.length-1 < n
		fac << fac.last * fac.length
	end
	print fac[n].to_s + (x+1 == t ? "" : "\n")
end
