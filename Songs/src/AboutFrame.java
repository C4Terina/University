import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AboutFrame extends JFrame {

    public AboutFrame() {
        JPanel panel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        JLabel aboutMessage = new JLabel();
        aboutMessage.setText("<html><h3>Kat's song app</h3><br>"
                + "This application was made by Aikaterini Papachristodoulou 19390185 6th semester "
                + "<br><strong>Finished date: 9/6/2022 </strong></html>");

        ImageIcon icon = new ImageIcon("icon.png");
        Image screenImage = icon.getImage();
        Image modifiedScreenImage = screenImage.getScaledInstance(1080, 600, Image.SCALE_SMOOTH);
        icon = new ImageIcon(modifiedScreenImage);
        JOptionPane.showMessageDialog(AboutFrame.this, "", "The IDE used for the project is \"IntelliJ IDEA\"", JOptionPane.INFORMATION_MESSAGE, icon);

        this.add(aboutMessage);
        JButton okBtn = new JButton("Ok");
        panel.add(okBtn);
        this.add(panel, BorderLayout.PAGE_END);

        ImageIcon image2 = new ImageIcon("icon.png"); //create an image icon
        this.setIconImage(image2.getImage()); //change icon of frame

        //ok button closes the window
        okBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setVisible(false);
                dispose(); //Destroy the JFrame object
            }
        });

        //setup the frame
        this.setSize(300, 300);
        this.setResizable(true);
        this.setLocationRelativeTo(null);
        this.setTitle("About");
        this.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        this.setVisible(true);
    }
}
