const int INPUT_NODES = 2;
const int OUTPUT_NODES = 3;

double input[INPUT_NODES] = {1,2};
double output[OUTPUT_NODES];
double weight[INPUT_NODES][OUTPUT_NODES] = {{1,2,3},{4,5,6}};
double bias[OUTPUT_NODES] = {7,8,9};

typedef enum _activation {
       LINEAR=0,
       SIGMOID=1,
       RELU=2,
} activation_t;

void feed_forward(
const double *input,
const double * weight,
const double *bias,
double *output,
const int INPUT_NODES,
const int OUTPUT_NODES,
activation_t activation) {
              for(int j=0;j<OUTPUT_NODES;j++) {
                     double sum = 0.0;
                     for(int i=0;i<INPUT_NODES;i++) {
                            sum += input[i]*weight[i*OUTPUT_NODES+j];
                     }
                     sum += 1*bias[j];
                     if(activation==LINEAR) {
                            output[j] = sum;
                     } else if(activation==SIGMOID) {
                            output[j] = 1.0/(1.0+exp(-sum));
                     } else if(activation==RELU) {      
                            output[j] = sum>0?sum:0;
                     } 
                     
                     printf("output[%d] = %f\n", j, output[j]);       
              }
       }

void setup() {
       Serial.begin(115200);
       delay(1000); 

      feed_forward(input,
      (const double *)weight,
      bias,
      output,
      INPUT_NODES,
      OUTPUT_NODES,
      SIGMOID);
}

void loop() {
      
}