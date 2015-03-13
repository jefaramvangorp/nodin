
name = "WriteTextFile"
num_inputs = 2
num_outputs = 0
input_types = { "string", "string" }
output_types = {}

function evaluateForOutput(outputIndex)
    local file_name = ndn_inputs.string(0)
    local text = ndn_inputs.string(1)
    local file = assert(io.open(file_name, "w"))
    file:write(text)
    file:close()
    ndnLogMessage("Done writing text to file: " .. file_name);
    -- no output
end


