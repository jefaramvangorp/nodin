
-- The name or type of the node (must be unique!).
name = "Logger"

-- The number of inputs and outputs the node has.
num_inputs = 1
num_outputs = 0

-- The types associated to the inputs/outputs (the size of each array must match the corresponding number given above).
input_types = { "any" }
output_types = {}

-- Evaluates the value for the output with given index. This function performs the actual logic of the node.
function evaluateForOutput(outputIndex)
    ndnLogMessage(ndn_inputs.string(0))
end


