class ListNode
{
    public ListNode back;
    public ListNode fwd;

    public final int id;

    public static int nextId = 0;

    public ListNode()
    {
        id = nextId++;
    }

    public void addAfter(final ListNode back)
    {
        this.back = back;
        this.fwd = this.back.fwd;

        back.fwd = this;
        if (fwd != null) fwd.back = this;
    }

    public void unlink()
    {
        if (back != null)
        {
            back.fwd = fwd;
        }
        else
        {
            App.startPtr = fwd;
        }

        if (fwd != null) fwd.back = back;
    }
}
