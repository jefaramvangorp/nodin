
name = "Logger"
num_inputs = 1
num_outputs = 0
input_types = { "any" }
output_types = {}

function evaluateForOutput(outputIndex)
    ndnLogMessage(ndn_inputs.string(0))
end


