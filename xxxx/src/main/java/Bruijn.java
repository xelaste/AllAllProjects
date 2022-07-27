import java.util.*;

public class Bruijn {
        static Set<String> seen = new HashSet<String>();
        static Vector<Integer> edges = new Vector<Integer>();

        // Modified DFS in which no edge
        // is traversed twice
        static void dfs(String node, int k, String A)
        {
            System.out.println(node);
            for (int i = 0; i < k; ++i)
            {
                String str = node + A.charAt(i);
                if (!seen.contains(str))
                {
                    seen.add(str);
                    dfs(str.substring(1), k, A);
                    edges.add(i);
                }
            }
        }

        // Function to find a de Bruijn sequence
        // of order n on k characters
        static String deBruijn(int n, int k, String A)
        {

            // Clearing global variables
            seen.clear();
            edges.clear();

            String startingNode = string(n - 1, A.charAt(0));
            dfs(startingNode, k, A);

            String S = "";

            // Number of edges
            int l = (int) Math.pow(k, n);
            for (int i = 0; i < l; ++i)
                S += A.charAt(edges.get(i));
            S += startingNode;
        System.out.println(edges);
            return S;
        }

        private static String string(int n, char charAt)
        {
            String str = "";
            for (int i = 0; i < n; i++)
                str += charAt;
            return str;
        }

        // Driver code
        public static void main(String[] args)
        {
            int n = 3, k = 2;
            String A = "01";

            System.out.print(deBruijn(n, k, A));
        }
    }

