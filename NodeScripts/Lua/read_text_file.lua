
name = "ReadTextFile"
num_inputs = 1
num_outputs = 1
input_types = { "string" }
output_types = { "string" }

function evaluateForOutput(outputIndex)
    local file_name = ndn_inputs.string(0)
    local file = assert(io.open(file_name, "r"))
    local text = file:read("*all")
    file:close()
    return text
end


