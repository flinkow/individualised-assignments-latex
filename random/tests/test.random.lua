package.path = package.path .. ";../?.lua;../../symcomp/?.lua"

local random = require "random"

local factory = 
{
    { "a", 5 },
    { "b", 4 },
    { "n", 2 }
}

ex = random.create("a*x**n+b", factory)

assert(ex == "5*x**2+4")

print("All tests succeeded.")