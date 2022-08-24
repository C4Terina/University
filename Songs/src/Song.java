public class Song{ //Η κλάση song με όλα τα απαραίτητα fields
    private String songID;
    private String date;
    private String title;
    private String duration;
    private String artist;
    private String genre;

    public Song(String songID, String date, String title, String duration, String artist, String genre){
        this.songID = songID;
        this.date = date;
        this.title= title;
        this.duration=duration;
        this.artist=artist;
        this.genre=genre;
    }

    //Getters και Setters
    public String getSongID() { return songID; }

    public void setSongID(int songID) { this.songID = String.valueOf(songID); }

    public String getGenre() { return genre; }

    public void setGenre(String genre) { this.genre = genre; }

    public String getIssueDate() { return date; }

    public void setIssueDate(String issueDate) { this.date = issueDate; }

    public String getTitle() { return title; }

    public void setTitle(String title) { this.title = title; }

    public String getDuration() { return duration; }

    public void setDuration(String duration) { this.duration = duration; }

    @Override
    public String toString(){
        return songID + "\t" +  title + "\t" + date + "\t" + duration + "\t " + artist + "\t" + genre;
    }
}


