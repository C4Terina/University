import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.util.*;

public class MainFrame extends JFrame {
    public static int songID = 1;
    private JLabel titleLabel, durationLabel, dateLabel, artistLabel, genreLabel, browsingLabel;
    private JTextField title, date , duration, artist;
    private JComboBox genre;
    private JButton aboutBtn, insertBtn, saveBtn, exitBtn, statisticsBtn;
    public JTextArea area;
    private String fileName= "songlist.txt";
    private ArrayList<Song> songList = new ArrayList();
    private JMenuBar menuBar;
    private JMenu fileMenu;
    private JMenu helpMenu;
    private JMenuItem saveItem;
    private JMenuItem insertItem;
    private JMenuItem statisticsItem;
    private JMenuItem exitItem;
    private JMenuItem aboutItem;

    public MainFrame(){

        // Η διαδικασία που ακολουθούμε για να προετοιμάσουμε το window είναι η ίδια που είδαμε με του main frame.
        this.setSize(780,420);
        this.setTitle("Insert new song");
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setLayout(null);
        this.setResizable(false); // Αφαιρούμε από τον χρήστη την δυνατότητα να κάνει resize το window

        System.setProperty("bgrd","0XD0E2F4");
        this.getContentPane().setBackground(Color.getColor("bgrd"));

        Image icon = Toolkit.getDefaultToolkit().getImage("icon.png");
        this.setIconImage(icon);

        //Καλούμε όλες τις απαραίτητες συναρτήσεις για να μας δημιουργηθεί το window
        prepareMenu();
        prepareTexts();
        prepareButtons();

        this.setVisible(true);
    }

    public void prepareMenu(){ //Μέθοδος για να αρχικοποιήσουμε τo Menu
        menuBar = new JMenuBar();
        fileMenu = new JMenu("File");
        helpMenu = new JMenu("Help");

        this.menuBar = new JMenuBar();
        this.fileMenu = new JMenu("File");

        this.saveItem = new JMenuItem("Save to file");
        this.exitItem = new JMenuItem("Exit");
        this.insertItem = new JMenuItem("Insert songs");
        this.statisticsItem = new JMenuItem("Statistics tab");
        this.aboutItem = new JMenuItem("About");

        this.saveItem.addActionListener(e -> save());
        this.exitItem.addActionListener(e -> exitApp());
        this.insertItem.addActionListener(e -> getText());
        this.statisticsItem.addActionListener(e -> statistic());
        this.aboutItem.addActionListener(e -> about());

        fileMenu.add(insertItem);
        fileMenu.add(saveItem);
        fileMenu.add(statisticsItem);
        fileMenu.addSeparator();
        fileMenu.add(exitItem);

        helpMenu.add(aboutItem);
        menuBar.add(fileMenu);
        menuBar.add(helpMenu);

        this.setJMenuBar(menuBar);
    }

    public void prepareButtons(){ //Μέθοδος για να αρχικοποιήσουμε τα buttons
        System.setProperty("color","0XE1EDF8");

        insertBtn = new JButton("Insert");
        this.insertBtn.setBackground(Color.getColor("color"));
        this.insertBtn.setBounds(100, 320, 100, 30);
        this.add(this.insertBtn);
        add(insertBtn);
        insertBtn.addActionListener(e -> getText());


        saveBtn = new JButton("Save");
        this.saveBtn.setBackground(Color.getColor("color"));
        this.saveBtn.setBounds(205, 320, 80, 30);
        this.add(this.saveBtn);
        add(saveBtn);
        saveBtn.addActionListener(e -> save());

        statisticsBtn = new JButton("Statistics");
        this.statisticsBtn.setBackground(Color.getColor("color"));
        this.statisticsBtn.setBounds(290, 320, 110, 30);
        this.add(this.statisticsBtn);
        add(statisticsBtn);
        statisticsBtn.addActionListener(e -> statistic());

        aboutBtn = new JButton("About");
        this.aboutBtn.setBackground(Color.getColor("color"));
        this.aboutBtn.setBounds(15, 320, 80, 30);
        this.add(this.aboutBtn);
        add(aboutBtn);
        aboutBtn.addActionListener(e -> about());

        exitBtn = new JButton("Exit");
        this.exitBtn.setBackground(Color.getColor("color"));
        this.exitBtn.setBounds(405, 320, 80, 30);
        this.add(this.exitBtn);
        add(exitBtn);
        exitBtn.addActionListener(e -> exitApp());
    }

    public void prepareTexts(){//Μέθοδος για να αρχικοποιήσουμε τα texts
        titleLabel = new JLabel("Title: ");
        titleLabel.setForeground(Color.BLACK);
        titleLabel.setBounds(10,10,50,30);
        titleLabel.setFont(new Font("Arial",Font.PLAIN,15));
        add(titleLabel);

        durationLabel = new JLabel("Duration:");
        durationLabel.setForeground(Color.BLACK);
        durationLabel.setBounds(10,42,800,30);
        durationLabel.setFont(new Font("Arial",Font.PLAIN,15));
        add(durationLabel);

        dateLabel = new JLabel("Date:");
        dateLabel.setForeground(Color.BLACK);
        dateLabel.setBounds(10,75,40,30);
        dateLabel.setFont(new Font("Arial",Font.PLAIN,15));
        add(dateLabel);

        artistLabel = new JLabel("Artist:");
        artistLabel.setForeground(Color.BLACK);
        artistLabel.setBounds(10,110,80,30);
        artistLabel.setFont(new Font("Arial",Font.PLAIN,15));
        add(artistLabel);

        genreLabel = new JLabel("Genre:");
        genreLabel.setForeground(Color.BLACK);
        genreLabel.setBounds(10,140,80,30);
        genreLabel.setFont(new Font("Arial",Font.PLAIN,15));
        add(genreLabel);

        browsingLabel = new JLabel("(Please fill all the areas)");
        browsingLabel.setForeground(Color.BLACK);
        browsingLabel.setFont(new Font("Arial",Font.BOLD,14));
        browsingLabel.setBounds(15,280,300,30);
        add(browsingLabel);


        //Text fields
        title = new JTextField();
        title.setBounds(90,18,150,20);
        add(title);

        duration = new JTextField();
        duration.setBounds(90,48,150,20);
        add(duration);

        date = new JTextField();
        date.setBounds(90,80,150,20);
        add(date);

        artist = new JTextField();
        artist.setBounds(90,115,150,20);
        add(artist);

        //Combo box
        String option[] = new String[]{"Rock", "Pop", "Metal","Speedcore","Breakcore","Dark Synthwave", "Hardstyle", "Hardcore", "Hyperpop", "Digicore", "Chiptune", "Glitchcore", "Vocaloids"};
        this.genre = new JComboBox(option);
        this.genre.setBounds(90, 145, 150, 20);
        this.add(this.genre);

        area = new JTextArea();
        area.setBounds(300,18, 400,270);
        area.setEditable(false);
        area.setBorder(BorderFactory.createTitledBorder(BorderFactory.createEtchedBorder()));
        System.setProperty("areaColor","0XD9E8F6");
        area.setBackground(Color.getColor("areaColor"));
        add(area);
    }

    //********************** private methods which implement the required functionality **********************

    private void insertSong(String songID, String date, String title, String  duration, String artist, String genre){
        area.setText("");
        Song song =  new Song(songID, date, title, duration, artist, genre);

        songList.add(song);

        area.append(""); //Για να εμφανιστούν αυτα που βάλαμε στο text area
        area.append("Song ID: \t"+ songID +
                "\n\nTitle: \t"+ title +
                "\n\nDuration:  \t"+ date+
                "\n\nRelease Date: \t"+ duration+
                "\n\nArtist: \t"+ artist +
                "\n\nGenre: \t"+ genre);
        area.append("\n");
    }
    private void save(){
        saveBtn.setEnabled(true);
        try {
            FileWriter fw = new FileWriter(fileName, true);
            BufferedWriter writer = new BufferedWriter(fw);

            //Εγγραφη τραγουδιού σε txt αρχείο το ένα κάτω απο το άλλο
            for(Song song:songList){
                writer.write(song.toString());
                writer.newLine();
            }

            writer.close();

            //Εμφανίζει ένα pop up message πως αποθηκεύτηκε επιτυχώς το τραγούδι
            JOptionPane.showMessageDialog(
                    MainFrame.this,
                    "Your song list is saved in " + fileName,
                    "Save Completed",
                    JOptionPane.INFORMATION_MESSAGE);

            //Μόλις γίνει η αποθήκευση του τραγουδιου ενεργοποιούνται ξανα τα buttons
            saveBtn.setEnabled(true);
            insertBtn.setEnabled(true);
            clearInput();
        } catch (IOException e) {
            JOptionPane.showMessageDialog(saveBtn,
                    "Can't access " + fileName,
                    "File access error",
                    JOptionPane.ERROR_MESSAGE);
        }
    }
    private void statistic(){
        new Statistics(); //καλεί την κλάση statistics
    }
    private void about(){
        new AboutFrame(); //καλεί την κλάση about
    }

    public void clearInput() { //Μέθοδος για να γίνεται clear το text area
        this.title.setText("");
        this.duration.setText("");
        this.date.setText("");
        this.artist.setText("");
        this.genre.setSelectedIndex(0);
        this.insertBtn.setEnabled(true);
        this.saveBtn.setEnabled(true);
    }

    public void getText() {
        // Αποθηκεύουμε σε string variables τα δεδομένα απο τα textfields.
        String name = title.getText();
        String dur = duration.getText();
        String dates = date.getText();
        String art = artist.getText();
        String gen = (String)this.genre.getItemAt(this.genre.getSelectedIndex());
        if (!name.isEmpty() && !dur.isEmpty() && !dates.isEmpty() && !art.isEmpty() && !gen.isEmpty()) {
                this.insertSong(String.valueOf(songID), name, dur, dates, art, gen);
                songID++;
        } else {
            JOptionPane.showMessageDialog(this, "You need to fill all the blank spaces!", "Insert song error!", 2);
        }
    }

    //Μέθοδος για το κλείσιμο της εφαμοργής. Αν επιλεγεί το "yes" τότε η εφαρμογή τερματίζεται
    private void exitApp() {
        int i = JOptionPane.showConfirmDialog(MainFrame.this, "Do you want to exit the app?");
        if (i == JOptionPane.YES_OPTION) {
            System.exit(0);
        }
    }
}
