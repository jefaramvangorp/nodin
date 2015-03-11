
-- The name or type of the node (must be unique!).
name = "Add"

-- The number of inputs and outputs the node has.
num_inputs = 2
num_outputs = 1

-- The types associated to the inputs/outputs (the size of each array must match the corresponding number given above).
input_types = { "float", "float" }
output_types = { "float" }

-- Evaluates the value for the output with given index. This function performs the actual logic of the node.
function evaluateForOutput(outputIndex)
    return ndn_inputs.float(0) + ndn_inputs.float(1)
end

-- A list of the required parameters to create a node of this type.
required_parameters = {}

-- Validates the parameters with given name and value.
function validateParameter(name, value)
    return true
end


