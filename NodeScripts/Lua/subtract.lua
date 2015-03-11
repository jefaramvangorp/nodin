
name = "Subtract"
num_inputs = 2
num_outputs = 1
input_types = { "float", "float" }
output_types = { "float" }

function evaluateForOutput(outputIndex)
    return ndn_inputs.float(0) - ndn_inputs.float(1)
end

-- no parameters needed
required_parameters = {}
function validateParameter(name, value)
    return true
end


