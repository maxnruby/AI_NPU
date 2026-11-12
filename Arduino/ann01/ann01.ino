const int INPUT_NODES = 2;
const int OUTPUT_NODES = 3;

double input[INPUT_NODES] = {1,2};
double output[OUTPUT_NODES];
double weight[INPUT_NODES][OUTPUT_NODES] = {{1,2,3},{4,5,6}};
double bias[OUTPUT_NODES] = {7,8,9};

void setup() {
       Serial.begin(115200);
       delay(1000); 

       for(int j=0;j<OUTPUT_NODES;j++) {
            double sum = 0.0;
            for(int i=0;i<INPUT_NODES;i++) {
                  sum += input[i]*weight[i][j];
                  }
                  sum += 1*bias[j];
                  output[j] = sum;
                  printf("sum = %f\n", sum);
       }
}

void loop() {
      
}