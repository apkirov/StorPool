import java.io.*;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.util.*;
import java.util.concurrent.ArrayBlockingQueue;

public class JsonReader {
    private HashMap<String, Integer> hModels = new HashMap<>();
    private class Worker extends Thread {
        private ArrayBlockingQueue<String> theRow = null;


        public Worker (ArrayBlockingQueue<String> theRow) {
            this.theRow = theRow;
        }

        public void parseElement (String element ) {
            int start = element.indexOf("\"model\":\"")+9;
            int end = element.indexOf("\"", start);
            if (start > 0 && end > 0) {
                String model = element.substring(start, end);
                if (hModels.get(model) != null) {
                    hModels.put(model, hModels.get(model) + 1);

                }
                else {
                    hModels.put(model, 1);
                }
            }

//            System.err.println("String: "+ element +", Start: "+ start+", End: "+ end);
//            System.err.println(model);


        }

        public void run() {
            while( true ) {
                try {
                    String res = this.theRow.take();
                    if ("__END__".equals(res)) {
                        break;
                    }
                    if (res != null) {
//                        System.err.println("Start parsing");
                        parseElement((res));
//                        System.err.println("Parsing done");
                    }
                }
                catch(InterruptedException ex) {
                    ex.printStackTrace();
                    break;
                }

            }
        }
    }


    public void doit(String fileName) {
        try {
            int cores = Runtime.getRuntime().availableProcessors();
            ArrayBlockingQueue<String> theQueue = new ArrayBlockingQueue<String>(500000);
            final DecimalFormat df = new DecimalFormat("0.00");

            if (cores < 2) {
                cores = 2;
            }
            ArrayList<Worker> workers = new ArrayList<>(cores - 1);
            for(int uh1 = 0; uh1 < cores - 1; uh1++) {
                Worker worker = new Worker(theQueue);
                worker.start();
                workers.add(worker);
            }


            Reader inputStreamReader = new InputStreamReader(new FileInputStream(fileName));
            Path path = Paths.get(fileName);
            long bytes = Files.size(path);


            StringBuilder str = new StringBuilder();
            long uIter = 0;
            while (true) {
                uIter++;
                if (uIter % 10000000 == 0) {
                    System.out.print("\r"+ uIter + " from "+ bytes + " -- "+((float)uIter/(float)bytes) *100 +"%");
                }
                int data = inputStreamReader.read();
                if (data == -1) {
                    break;
                }
                if (data == '}') {
                    str.append((char) data);
                    theQueue.put(str.toString());
                    str.setLength(0);
                }
                str.append((char) data);
            }
            inputStreamReader.close();
            for (int uh1 = 0; uh1 < workers.size(); uh1++) {
                theQueue.put("__END__");
            }
            System.out.println("\n");
            while (true) {
                boolean isAlive = false;
                for (Worker worker : workers) {
                    isAlive  =  isAlive || worker.isAlive();
                }
                if (!isAlive) {
                    break;
                }
                Thread.sleep(10);
            }
            System.out.println("Number of models is: " + hModels.keySet().size());

            List<Map.Entry<String, Integer> > list
                    = new ArrayList<Map.Entry<String, Integer> >(
                    hModels.entrySet());

            Collections.sort(
                    list,
                    new Comparator<Map.Entry<String, Integer> >() {
                        // Comparing two entries by value
                        public int compare(
                                Map.Entry<String, Integer> entry1,
                                Map.Entry<String, Integer> entry2)
                        {

                            // Substracting the entries
                            return entry2.getValue()
                                    - entry1.getValue();
                        }
                    });
            int uh1 =  0;
            for (Map.Entry<String, Integer> l : list) {

                // Printing the sorted map
                // using getKey()  and getValue() methods
                System.out.println("First 10. Key ->"
                        + " " + l.getKey()
                        + ": Value ->"
                        + l.getValue());
                if (uh1++ > 10) {
                    break;
                }
            }



        }
        catch(InterruptedException  ex) {
            ex.printStackTrace();
            System.exit(0);
        }
        catch(FileNotFoundException ex) {
            ex.printStackTrace();
            System.exit(0);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            System.exit(0);

        }


    }


    public static void main(String []args) {
        String fileName = args[0];
        JsonReader jsonReader = new JsonReader();
        jsonReader.doit(fileName );

    }
}
