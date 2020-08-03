import java.util.Random;

class App
{
    public static final int MAX_ITERATIONS = 1_000_000;
    public static final int SMALL_LIST_SIZE = 2000;
    public static final int MEDIUM_LIST_SIZE = 4500;
    public static final int LARGE_LIST_SIZE = 9000;

    public static ListNode startPtr = new ListNode();
    public static int listSize = 0;
    public static Random rand = new Random();

    public static void main(String... args)
    {
        System.out.println("List test");

        for (int i = 0; i < 200; i++)
        {
            addNode();
        }

        System.out.println("Starting small list");
        modifyList(SMALL_LIST_SIZE);

        System.out.println("Starting medium list");
        modifyList(MEDIUM_LIST_SIZE);

        System.out.println("Starting large list");
        modifyList(LARGE_LIST_SIZE);
    }

    public static void modifyList(final int averageListSize)
    {
        long totalTime = 0;
        for (int i = 0; i < MAX_ITERATIONS; i++)
        {
            long loopStartTime = System.nanoTime();
            double removalRate = ((double)listSize) / (averageListSize * 2);

            if (rand.nextDouble() > removalRate)
            {
                addNode();
            }
            else
            {
                removeNode();
            }

            totalTime += System.nanoTime() - loopStartTime;
        }

        System.out.println("Loop time: " + ((double)totalTime / MAX_ITERATIONS));
    }

    public static void addNode()
    {
        double  positionDouble = rand.nextDouble() * listSize;
        int position = (int)(positionDouble);
        ListNode node = startPtr;

        for (int i = 0; i < position; i++)
        {
            node = node.fwd;
        }

        if (node == null)
        {
            throw new RuntimeException(positionDouble + " " + position + " " + listSize);
        }

        ListNode newNode = new ListNode();
        newNode.addAfter(node);

        listSize++;
    }

    public static void removeNode()
    {
        double  positionDouble = rand.nextDouble() * listSize;
        int position = (int)(positionDouble);

        ListNode node = startPtr;
        for (int i = 0; i < position; i++)
        {
            node = node.fwd;
        }

        if (node == null)
        {
            throw new RuntimeException(positionDouble + " " + position + " " + listSize);
        }
        node.unlink();

        listSize--;
    }
}
