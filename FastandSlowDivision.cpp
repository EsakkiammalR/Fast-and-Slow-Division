module Division (
    input wire [31:0] dividend,
    input wire [31:0] divisor,
    output reg [31:0] quotient,
    output reg [31:0] remainder
);

    always @(dividend, divisor) begin
        quotient = 0;
        remainder = dividend;

        // Slow Division Algorithm
        while (remainder >= divisor) begin
            remainder = remainder - divisor;
            quotient = quotient + 1;
        end

        // Fast Division Algorithm
        reg [31:0] bitPosition = 1;
        reg [31:0] tempDivisor = divisor;

        while (tempDivisor <= remainder) begin
            tempDivisor = tempDivisor << 1;
            bitPosition = bitPosition << 1;
        end

        while (bitPosition > 1) begin
            tempDivisor = tempDivisor >> 1;
            bitPosition = bitPosition >> 1;

            if (remainder >= tempDivisor) begin
                remainder = remainder - tempDivisor;
                quotient = quotient + bitPosition;
            end
        end
    end

endmodule

module DivisionTestbench;
    reg [31:0] dividend = 10;
    reg [31:0] divisor = 3;
    reg [31:0] quotient;
    reg [31:0] remainder;

    // Instantiate the Division module
    Division uut (
        .dividend(dividend),
        .divisor(divisor),
        .quotient(quotient),
        .remainder(remainder)
    );

    initial begin
        // Slow Division
        #10;
        $display("Slow Division:");
        $display("Quotient: %d", quotient);
        $display("Remainder: %d", remainder);

        // Fast Division
        #10;
        $display("Fast Division:");
        $display("Quotient: %d", quotient);
        $display("Remainder: %d", remainder);

        $finish;
    end

endmodule
