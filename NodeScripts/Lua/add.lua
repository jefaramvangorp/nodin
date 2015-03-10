
function split(str, sep)
    if sep == nil then
        sep = "%s"
    end

    local t = {} ; i = 1
    for str in string.gmatch(str, "([^"..sep.."]+)") do
        t[i] = str
        i = i + 1
    end
    return t
end


name = "Add"
num_inputs = 2
num_outputs = 1
input_types = { "float", "float" }
output_types = { "float" }

function evaluateForOutput(inputs, outputIndex)
    local input = split(inputs, ",")
    return input[1] + input[2]
end

required_parameters = {}
function validateParameter(name, value)
    return true
end


